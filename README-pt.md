# AsyncHook ⏳ 🎣

Um hook simples para lidar de forma sana com promises em ReasonReact permitindo que você passe argumentos para a chamada.

```reason
[@react.component]
let make = () => {
  let ({state: createUserState}, createUser) = AsyncHook.use((~cb, ~name, ~age) => cb(() => {
    fetch("/user", ~params={
      name,
      age,
    })
  }))


  let onSubmit= () => {
    createUser(~name=form.values.name, ~age=form.values.age)
    // Handle the result after the call
    |> Promise.tapError(error => {
      Js.log(error)
    })
    |> Promise.getOk(result => {
      Js.log("Success!")
    })
  }

  // or use the declarative mode
  <div>
    {
      switch(createUserState) {
        | Idle => <button onClick={_ => onSubmit()}>"Create user"->React.string</button>
        | Loading => <p>{"Loading..."->React.string}</p>
        | Error(error) => 
          <p>
            "User created with id #"->React.string
            {data.user.id->React.string}
          </p>
        | Data(data) =>
          <p>
            "User created with id #"->React.string
            {data.user.id->React.string}
          </p>
      }
    }
  </div>
}
```

# Instalação

```
yarn add reason-async-hook reason-promise
```

`bsconfig.json`
```json
  "bs-dependencies": [
    "reason-async-hook",
    "reason-promise"
  ]
```

Promises são apenas melhores com reason-promise!

# How does it work

A lib apenas usa o currying por padrão e a inferência de tipos mágica do ReasonML.
`reason-promise` roda em cima das promises JavaScript mas ele adiciona mais funcionalidades a elas, e uma delas é o suporte ao tipo `result`. Permitindo controle fino sobre o fluxo da chamada e permitindo _railway programming_.
