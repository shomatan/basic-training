import Instruction.Instruction

import scala.collection.immutable.HashMap
import scala.io.Source
import scala.util.Try

sealed trait VMError
case object ParsingError extends VMError
case object SyntaxError extends VMError
case class UnknownInstructionError(instruction: String) extends VMError
case object RuntimeError extends VMError
case class NotEnoughArgument(require: Int) extends VMError
case class InvalidType(type1: OperandType, type2: OperandType) extends VMError


object Stack {
  def pop[A](stack: List[A]): (A, List[A]) = {
    if (stack.isEmpty) {
      throw new RuntimeException("Empty stack")
    } else {
      val value = stack.head
      (value, stack.tail)
    }
  }

  def pop2[A](stack: List[A]): (A, A, List[A]) = {
    if (stack.length < 2) {
      throw new RuntimeException("Empty stack")
    } else {
      val value = stack.head
      val value2 = stack.tail.head
      (value, value2, stack.tail.tail)
    }
  }
}

object Instruction {

  type Instruction = List[Operand] => Either[VMError, List[Operand]]

  def add(): Instruction =
    stack =>
      if (stack.length >= 2) {
        val (first, second, newStack) = Stack.pop2(stack)
        if (first.`type` != second.`type`)
          Left(NotEnoughArgument(2))
        else {
          for {
            result <- first + second
            next = result :: newStack
          } yield next
        }
      } else
        Left(NotEnoughArgument(2))

  def sub(): Instruction =
    stack =>
      if (stack.length >= 2) {
        val (first, second, newStack) = Stack.pop2(stack)
        if (first.`type` != second.`type`)
          Left(NotEnoughArgument(2))
        else {
          for {
            result <- first - second
            next = result :: newStack
          } yield next
        }
      } else
        Left(NotEnoughArgument(2))

  def div(): Instruction =
    stack =>
      if (stack.length >= 2) {
        val (first, second, newStack) = Stack.pop2(stack)
        if (first.`type` != second.`type`)
          Left(NotEnoughArgument(2))
        else {
          for {
            result <- first / second
            next = result :: newStack
          } yield next
        }
      } else
        Left(NotEnoughArgument(2))

  def push(operand: Operand): Instruction =
    stack =>
      Right(operand :: stack)

  def printStack(): Instruction =
    stack => {
      println("==============")
      stack.foreach(println)
      println("=============")
      println()
      Right(stack)
    }
}

sealed trait OperandType
case object IntegerType extends OperandType
case object FloatType extends OperandType

sealed trait Operand {
  type Value
  def `type`: OperandType
  def value: Value

  protected  def withTypeGuard(roperand: Operand, f: (Value, Value) => Value): Either[VMError, Operand]
  def +(roperand: Operand): Either[VMError, Operand]
  def -(roperand: Operand): Either[VMError, Operand]
  def /(roperand: Operand): Either[VMError, Operand]
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

  def /(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, quot)

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

  def /(roperand: Operand): Either[VMError, Operand] =
    withTypeGuard(roperand, div)
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
    "print_stack" -> parsePrintStack
//    "fork" -> parseFork
  )

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


object ProgramInterpreter {

  type Program = Seq[Instruction]

  def run(program: Program): List[Operand] = {

    program.foldLeft(List.empty[Operand]) {
      case (stack, instruction) =>
        instruction(stack).fold(
          error => {
            println(error)
            stack
          },
          newStack => newStack
        )
    }
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
        ProgramInterpreter.run(instructions)
        println("Finished")
      }
    )
  }
}
