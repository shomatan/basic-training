import java.time.ZonedDateTime

/*
import Result.Result
import cats.Monad
import cats.data.EitherT
import monix.eval.Task

import scala.concurrent.Future

case class User(
  name: String,
  password: String
)

case class LogItem(
  created: ZonedDateTime,
  message: String
)
sealed trait AppError extends RuntimeException

object Result {
  type Result[F[_], A] = F[Either[AppError, A]]


  def success[F[_]: Monad, A](a: A): Result[F, A] = {
    val monadInstance = implicitly[Monad[F]]
    monadInstance.pure(Right(a))
  }

  def error[F[_]: Monad, A](error: AppError): Result[F, A] = {
    val monadInstance = implicitly[Monad[F]]
    monadInstance.pure(Left(error))
  }

  object syntax {
    implicit class ResultOps[F[_], A](result: Result[F, A]) {
      def handleError: EitherT[F, AppError, A] =
        EitherT(result)
    }
  }
}

trait UserRepositoryAlg[F[_]] {
  def createUser(name: String, password: String): Result[F, User]
}


object UserRepository extends UserRepositoryAlg[Task] {
  override def createUser(name: String, password: String): Result[Task, User] =
    Result.success[Task, User](User(name, password))
}

trait LogRepositoryAlg[F[_]] {
  def appendLog(created: ZonedDateTime, message: String): F[LogItem]
}

object LogRepository extends LogRepositoryAlg[Task] {
  override def appendLog(created: ZonedDateTime, message: String): Result[Task, LogItem] =
    Result.success[Task, LogItem](LogItem(created, message))
}


class UserSevice[F[_]: Monad](userRepositoryAlg: UserRepositoryAlg[F], logRepositoryAlg: LogRepositoryAlg[F]) {
  import Result.syntax._
  def signup(name: String, password: String, repassword: String): Result[F, User] =
    (for {
      user <- userRepositoryAlg.createUser(name, password).handleError
      _ <- logRepositoryAlg..appendLog(ZonedDateTime.now(), s"user created $name").handleError
    } yield user).value
}

object Tagless {

  val userService = new UserSevice(UserRepository, LogRepository)
  userService.signup("", "", "")
}
*/