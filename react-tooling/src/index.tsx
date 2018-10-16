import { load, React, RootDispatcher, createDispatch } from "react-tooling"
import { Lens } from "monocle-ts"
import * as Profile from "./Profile"
import * as SignIn from "./SignIn"

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

const toUri = (route: Route): string => {
  switch (route.type) {
    case Home.type:
      return "";
    case SigninRoute.type:
      return "sign-in";
  }
}
const fromUri = (uri: string): Route => {
  switch (uri) {
    case "":
      return Home;
    case "sign-in":
      return SigninRoute;
    default:
      return Home;
  }
}

interface State {
  route: Route
  text: string
  profile: Profile.State
  signin: SignIn.State
}
const State: State = {
  route: Home,
  text: "hello",
  profile: Profile.State,
  signin: SignIn.State
}

const profileLens = Lens.fromProp<State, "profile">("profile")
const signinLens = Lens.fromProp<State, "signin">("signin")

type ViewProps = State & RootDispatcher<State, Route>

const View = ({ dispatch, setRoute, ...state }: ViewProps): JSX.Element => {
  switch (state.route.type) {
    case Home.type:
      return (
        <Profile.View
          {...state.profile}
          dispatch={createDispatch(dispatch, profileLens)}
        />
      );
    case SigninRoute.type:
      return (
        <SignIn.View
          {...state.signin}
          dispatch={createDispatch(dispatch, signinLens)}
        />
      );
    default:
      return <p>Not found</p>;
  }
}

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
