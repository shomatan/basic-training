import { load, React, RootDispatcher, createDispatch } from "react-tooling"
import { Lens } from "monocle-ts"
import * as Profile from "./Profile"

enum RouteType {
  Home = "Home",
  Signin = "Signin"
}

interface Home {
  type: RouteType.Home
}
const Home: Home = { type: RouteType.Home }

interface SigninRoute {
  type: RouteType.Signin
}
const SigninRoute: SigninRoute = { type: RouteType.Signin }

type Route = Home | SigninRoute

const toUri = (_: Route): string => ""
const fromUri = (_: string): Route => Home

interface State {
  route: Route
  text: string
  profile: Profile.State
}
const State: State = {
  route: Home,
  text: "hello",
  profile: Profile.State
}

const profileLens = Lens.fromProp<State, "profile">("profile")

type ViewProps = State & RootDispatcher<State, Route>

const View = ({ dispatch, setRoute, ...state }: ViewProps): JSX.Element => (
  <div>
    <Profile.View
      {...state.profile}
      dispatch={createDispatch(dispatch, profileLens)}
    />
  </div>
)

load(
  State,
  View,
  toUri,
  fromUri,
  module,
  {},
  {
    rootHTMLElement: document.getElementById("root")
  }
)
