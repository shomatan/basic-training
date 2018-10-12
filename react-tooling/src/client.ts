import * as axios from 'axios';

export interface Client {
  get(url: string): Promise<any>
  post(url: string, data: any): Promise<any>
}

const config: axios.AxiosRequestConfig = {
  headers: {
    'Content-Type': 'application/json'
  }
}

export const AxiosClient = (): Client => ({
  get: (url: string): Promise<any> =>
    axios.default.get<any>(url, config)
      .then(response => response.data),
  post: (url: string, data: any): Promise<any> =>
    axios.default.post<any>(url, data, config)
      .then(response => response.data)
})