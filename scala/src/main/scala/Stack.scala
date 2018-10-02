
// need ?
case class Stack2[A](first: A, second: A, newStack: List[A])

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