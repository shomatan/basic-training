import {
  RemoteData,
  Unloaded,
  Pending,
  Loaded,
  F1,
  Failed
} from "functools-ts"
import { Dispatcher, React } from "react-tooling"
import { AxiosClient } from "client"

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
  const user = await AxiosClient().get("https://google.com")
    .then(user => Loaded(user))
    .catch((err: Error) => Failed(err) as RemoteData<Error, User>)

  return (state: State) => ({
    ...state,
    user: user
  })
}

type ProfileProps = State & Dispatcher<State>
export const View = ({ dispatch, ...state }: ProfileProps): JSX.Element =>
  RemoteData.match(state.user, {
    Loaded: user => <div>Name: {user.name}</div>,
    Failed: err => <div>Error. {err.message}</div>,
    Pending: () => <div>Loading...</div>,
    Unloaded: () => {
      dispatch(startLoading)
      dispatch(getUser)
      return <div />
    }
  })
