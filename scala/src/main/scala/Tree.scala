

sealed trait Tree[+A]
case class Leaf[+A](value: A, left: Tree[A], right: Tree[A]) extends Tree[A]
case object Empty extends Tree[Nothing]

object Tree {
  def size[A](tree: Tree[A]): Int = {
    tree match {
      case Leaf(_, left, right) => size(left) + size(right) + 1
      case Empty => 0
    }
  }
  /*
 \ /
  |
  */
  def show[A](tree: Tree[A]): Int = {

  }

  def max[A](tree: Tree[A]): Int = ???
  def add[A](tree: Tree[A], value: A): Tree[A] = ???

}

object TreeTest {
  def main(args: Array[String]): Unit = {

    val tree1 = Empty
    val tree2 = Leaf(5, Empty, Empty)
    val tree3 = Leaf(6, tree2, tree1) // 2
    val tree4 = Leaf(7, tree3, Leaf(8, tree3, Empty))
    println(Tree.size(tree1))
    println(Tree.size(tree2))
    println(Tree.size(tree3))
    println(Tree.size(tree4))

    println(Tree.show(tree1))
    println(Tree.show(tree2))
    println(Tree.show(tree3))
    println(Tree.show(tree4))
  }
}