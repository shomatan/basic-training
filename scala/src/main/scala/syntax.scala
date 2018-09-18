
object EitherOps {
  def sequence[E, A](eithers: Seq[Either[E, A]]): Either[E, Seq[A]] =
    eithers.foldLeft(Right(Seq.empty[A]): Either[E, Seq[A]]) {
      case (Right(items), either) =>
        either.map(a => items :+ a)
      case (acc, _) =>
        acc
    }
}
