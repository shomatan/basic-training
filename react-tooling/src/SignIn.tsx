import { Dispatcher, React, memoizeComponent } from "react-tooling"
import { Lens } from "monocle-ts"

export interface State {
  username: string
  password: string
}

export const State: State = {
  username: "",
  password: ""
}

const setUsername = Lens.fromProp<State, "username">("username").set;
const setPassword = Lens.fromProp<State, "password">("password").set;

type ViewProps = State & Dispatcher<State>;
const Signin = ({ dispatch, ...state }: ViewProps): JSX.Element => (
  <form>
    <label>Username</label>
    <input
      type="text"
      id="username"
      onChange={evt => dispatch(setUsername(evt.target.value))}
    />
    <label>Password</label>
    <input
      type="password"
      onChange={evt => dispatch(setPassword(evt.target.value))}
    />
  </form>
);

export const View = memoizeComponent(Signin)