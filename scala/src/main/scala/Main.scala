import java.awt.peer.LightweightPeer

import scala.collection.immutable.HashMap
import scala.io.Source
import scala.util.Try

sealed trait VMError
case object ParsingError extends VMError
case object SyntaxError extends VMError
case class UnknownInstructionError(instruction: String) extends VMError
case object RuntimeError extends VMError
case class NotEnoughArgument(require: Int) extends VMError
case class InvalidArgument(expected: String) extends VMError
case class InvalidType(type1: OperandType, type2: OperandType) extends VMError


case class ProgramContext(stack: List[Operand], cursor: Int) {
  def next(stack: List[Operand], cursor: Int): ProgramContext =
    copy(stack = stack, cursor = cursor)
}

object Instruction {
  type Cursor = Int

  type Instruction = ProgramContext => Either[VMError, ProgramContext]

  def add(): Instruction =
    ctx =>
      if (ctx.stack.length >= 2) {
        val (first, second, newStack) = Stack.pop2(ctx.stack)
        for {
          result <- first + second
          stackResult = result :: newStack
        } yield ctx.next(stackResult, ctx.cursor + 1)
      } else
        Left(NotEnoughArgument(2))

  def sub(): Instruction =
    ctx =>
      if (ctx.stack.length >= 2) {
        val (first, second, newStack) = Stack.pop2(ctx.stack)
        for {
          result <- first - second
          stackResult = result :: newStack
        } yield ctx.next(stackResult, ctx.cursor + 1)
      } else
        Left(NotEnoughArgument(2))

  def div(): Instruction =
    ctx =>
      if (ctx.stack.length >= 2) {
        val (first, second, newStack) = Stack.pop2(ctx.stack)
        for {
          result <- first / second
          stackResult = result :: newStack
        } yield ctx.next(stackResult, ctx.cursor + 1)
      } else
        Left(NotEnoughArgument(2))

  def mul(): Instruction =
    ctx =>
      if (ctx.stack.length >= 2) {
        val (first, second, newStack) = Stack.pop2(ctx.stack)
        for {
          result <- first * second
          stackResult = result :: newStack
        } yield ctx.next(stackResult, ctx.cursor + 1)
      }
      else
        Left(NotEnoughArgument(2))

  def cmp(): Instruction =
    ctx =>
      if (ctx.stack.length >= 2) {
        val (first, second, newStack) = Stack.pop2(ctx.stack)
        for {
          result <- first.cmp(second)
          stackResult = result :: newStack
        } yield ctx.next(stackResult, ctx.cursor + 1)
      } else
        Left(NotEnoughArgument(2))

  def push(operand: Operand): Instruction =
    ctx =>
      Right(ctx.next(operand :: ctx.stack, ctx.cursor + 1))

  def printStack(): Instruction =
    ctx => {
      println("==============")
      ctx.stack.foreach(println)
      println("=============")
      println()
      Right(ctx.next(ctx.stack, ctx.cursor + 1))
    }

  def jump(address: Address): Instruction =
    ctx =>
      address.mode match {
        case Absolute =>
          Right(ctx.next(ctx.stack, address.cursor))
        case _ =>
          Left(UnknownInstructionError("relative not supported yet"))
      }
}

sealed trait OperandType
case object IntegerType extends OperandType
case object FloatType extends OperandType

sealed trait AddressMode
case object Absolute extends AddressMode
case object Relative extends AddressMode

case class Address(mode: AddressMode, cursor: Int)

sealed trait Operand {
  type Value
  def `type`: OperandType
  def value: Value

  protected  def withTypeGuard(roperand: Operand, f: (Value, Value) => Value): Either[VMError, Operand]
  def +(roperand: Operand): Either[VMError, Operand]
  def -(roperand: Operand): Either[VMError, Operand]
  def *(roperand: Operand): Either[VMError, Operand]
  def /(roperand: Operand): Either[VMError, Operand]

  def cmp(roperand: Operand): Either[VMError, Operand]
}
case class IntOperand(override val value: Int) extends Operand {
  type Value = Int
  override val `type`: OperandType = IntegerType

  import Numeric.IntIsIntegral._

  override protected def withTypeGuard(roperand: Operand, f: (Int, Int) => Int): Either[VMError, Operand] =
    roperand match {
      case IntOperand(rvalue) =>
        Right(IntOperand(f(value, rvalue)))
      case _ =>
        Left(InvalidType(this.`type`, roperand.`type`))
    }

  def +(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, plus)

  def -(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, minus)

  def *(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, times)

  def /(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, quot)

  def cmp(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, { (a, b) =>
      if (a == b) 0
      else if (a < b) -1
      else 1
    })

  /*def <=(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, )*/

}
case class FloatOperand(value: Float) extends Operand {
  type Value = Float
  override val `type`: OperandType = FloatType

  import Numeric.FloatIsFractional._

  override protected def withTypeGuard(roperand: Operand, f: (Float, Float) => Float): Either[VMError, Operand] =
    roperand match {
      case FloatOperand(rvalue) =>
        Right(FloatOperand(f(value, rvalue)))
      case _ =>
        Left(InvalidType(this.`type`, roperand.`type`))
    }

  def +(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, plus)

  def -(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, minus)

  def *(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, times)

  def /(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, div)

  def cmp(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, { (a, b) =>
      if (a == b) 0f
      else if (a < b) -1f
      else 1f
    })
}


object ProgramParser {

  import Instruction._

  type ParseResult = Either[VMError, Instruction]
  type ParseOperandResult = Either[VMError, Operand]
  type Parsers = HashMap[String, Seq[String] => ParseResult]

  private val separator = " "
  private val addressSeparator = ","
  val parsers: Parsers = HashMap(
    "push" -> parsePush,
    "add" -> parseAdd,
    "sub" -> parseSub,
    "div" -> parseDiv,
    "mul" -> parseMul,
    "jmp" -> parseJump,
    "print_stack" -> parsePrintStack,
    "cmp" -> parseCompare
//    "fork" -> parseFork
  )

  private[this] def parseCompare(args: Seq[String]): ParseResult =
    Right(Instruction.cmp())

  private[this] def parseJump(args: Seq[String]): ParseResult = {
    // abs:1 <- args(0)
    if (args.isEmpty)
      Left(NotEnoughArgument(1))
    else {
      val addressString = args(0).split(":")
      for {
        mode <-  addressString(0) match {
          case "abs" => Right(Absolute)
          case "rel" => Right(Relative)
          case _ => Left(InvalidArgument("abs|rel"))
        }
        cursor <- Try(addressString(1).toInt).map(c => Right(c)).getOrElse(Left(ParsingError))
      } yield jump(Address(mode, cursor))
    }
  }

  private[this] def parsePrintStack(args: Seq[String]): ParseResult =
    Right(printStack())

  private[this] def parsePush(args: Seq[String]): ParseResult =
    parseOperand(args.head).map(operand => push(operand))

  private[this] def parseAdd(args: Seq[String]): ParseResult =
    Right(add())

  private[this] def parseSub(args: Seq[String]): ParseResult =
    Right(sub())

  private[this] def parseDiv(args: Seq[String]): ParseResult =
    Right(div())

  private[this] def parseMul(args: Seq[String]): ParseResult =
    Right(mul())

  //private[this] def parseFork(args: Seq[String]): ParseResult =
    //Right(Fork)

  private[this] def parseFloat(word: String): ParseOperandResult =
    Try(word.toFloat).map(x => Right(FloatOperand(x))).getOrElse(Left(ParsingError))

  private[this] def parseAsciiCode(word: String): ParseOperandResult =
    Try(word.charAt(1).toInt).map(x => Right(IntOperand(x))).getOrElse(Left(ParsingError))

  private[this] def parseInt(word: String): ParseOperandResult =
    Try(word.toInt).map(x => Right(IntOperand(x))).getOrElse(Left(ParsingError))

  private[this] def parseOperand(word: String): ParseOperandResult =
    word match {
      case s if s.contains(".") => parseFloat(s)
      case s if s.charAt(0) == '\'' => parseAsciiCode(s)
      case s => parseInt(s)
    }

  // push <2.5|2|'c'> => ["push", "2.5"]
  def parse(line: String): ParseResult = {
    val words = line.split(separator)
    parsers
      .get(words(0))
      .map(parser => parser(words.tail))
      .getOrElse(Left(UnknownInstructionError(words(0))))
  }

}


object Main {

  def main(args: Array[String]): Unit = {

    // read line => transform => Program

    val lines = Source.fromFile("program.stack").getLines()
    val parsedInstructions = lines.map(ProgramParser.parse).toSeq

    EitherOps.sequence(parsedInstructions).fold(
      error =>
        println(error),
      instructions => {
        ProgramInterpreter.run(instructions.toIndexedSeq)
        println("Finished")
      }
    )
  }
}
