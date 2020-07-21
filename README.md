<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
[![All Contributors](https://img.shields.io/badge/all_contributors-3-orange.svg?style=flat-square)](#contributors-)
<!-- ALL-CONTRIBUTORS-BADGE:END -->

<p align="center">
  <br />
  <img src="./assets/logo.svg" width="700" /> 
</p>
<p align="center">
   <a href="#installation">Installation</a> • 
   <a target="_blank" href="#usage">Usage</a> •
   <a target="_blank" href="#how-does-it-work">How does it work</a>
</p>
<br/>
<br/>

## Usage

```reason
[@react.component]
let make = () => {
  let (AsyncHook.{state: createUserState}, createUser) = AsyncHook.use((~cb, ~name, ~age) => cb(() => {
    // It accepts anything that returns a Promise.t(result('a, 'e))
    fetch("/user", ~params={
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

## Contributors ✨

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="http://es77.fakenickels.dev"><img src="https://avatars0.githubusercontent.com/u/1283200?v=4" width="100px;" alt=""/><br /><sub><b>Gabriel Rubens</b></sub></a><br /><a href="https://github.com/reasonbr/reason-async-hook/commits?author=fakenickels" title="Code">💻</a> <a href="#ideas-fakenickels" title="Ideas, Planning, & Feedback">🤔</a> <a href="https://github.com/reasonbr/reason-async-hook/commits?author=fakenickels" title="Documentation">📖</a></td>
    <td align="center"><a href="http://vmarcosp.dribbble.com"><img src="https://avatars0.githubusercontent.com/u/20327229?v=4" width="100px;" alt=""/><br /><sub><b>Marcos Oliveira</b></sub></a><br /><a href="https://github.com/reasonbr/reason-async-hook/commits?author=vmarcosp" title="Documentation">📖</a> <a href="#design-vmarcosp" title="Design">🎨</a></td>
    <td align="center"><a href="http://guilherme.codes"><img src="https://avatars2.githubusercontent.com/u/8797405?v=4" width="100px;" alt=""/><br /><sub><b>Guilherme de Andrade</b></sub></a><br /><a href="https://github.com/reasonbr/reason-async-hook/commits?author=guilhermedeandrade" title="Documentation">📖</a></td>
  </tr>
</table>

<!-- markdownlint-enable -->
<!-- prettier-ignore-end -->
<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!
