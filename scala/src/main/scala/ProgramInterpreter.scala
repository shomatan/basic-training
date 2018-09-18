import Instruction.Instruction

import scala.annotation.tailrec

object ProgramInterpreter {

  type Program = IndexedSeq[Instruction]

  def run(program: Program): ProgramContext = {

    @tailrec
    def go(program: Program, ctx: ProgramContext): ProgramContext = {
      if (ctx.cursor >= 0 && ctx.cursor < program.length) {
        val instruction = program(ctx.cursor)
        instruction(ctx) match {
          case Left(error) =>
            println(error)
            ctx
          case Right(newCtx) =>
            go(program, newCtx)
        }
      } else
        ctx
    }
    go(program,  ProgramContext(List(), 0))
  }
}
