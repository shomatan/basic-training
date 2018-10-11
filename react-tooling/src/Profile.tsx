import {
  RemoteData,
  Unloaded,
  Pending,
  Loaded,
  F1
} from "functools-ts"
import { Dispatcher, React } from "react-tooling"

interface User {
  name: string
}

const User = (name: string): User => ({
  name: name
})

export interface State {
  user: RemoteData<Error, User>
}
export const State: State = {
  user: Unloaded()
}

const startLoading = (state: State): State => ({
  ...state,
  user: Pending()
})

const getUser = async (_: State): Promise<F1<State, State>> => {
  const user = Loaded(User("shoma"))

  return (state: State) => ({
    ...state,
    user: user
  })
}

type ProfileProps = State & Dispatcher<State>
export const View = ({ dispatch, ...state }: ProfileProps): JSX.Element =>
  RemoteData.match(state.user, {
    Loaded: user => <div>Name: {user.name}</div>,
    Failed: err => <div>Error. {err}</div>,
    Pending: () => <div>Loading...</div>,
    Unloaded: () => {
      dispatch(startLoading)
      dispatch(getUser)
      return <div />
    }
  })
