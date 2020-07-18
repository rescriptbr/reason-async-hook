# AsyncHook ⏳ 🎣

A simple hook for sane promise handling for ReasonReact.
Allowing you to pass additional arguments for the call using currying.

```reason
[@react.component]
let make = () => {
  let (AsyncHook.{state: createUserState}, createUser) = AsyncHook.use((~cb, ~name, ~age) => cb(() => {
    fetch("/use r", ~params={
      name,
      age,
    })
  }));

  let onSubmit= () => {
    createUser(~name=form.values.name, ~age=form.values.age)
    // Handle the result after the call
    |> Promise.tapError(error => {
      Js.log(error)
    })
    |> Promise.getOk(result => {
      Js.log("Success!")
    })
  };

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

# Installation

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

Promises are better with reason-promise!

# How does it work

We just leverage ReasonML currying and awesome type inference. `reason-promise` runs on top of
JavaScript promises but it adds more functionality to them, and the one we want is the `result` type one, allowing for fine-grained control over the call and railway programming.
