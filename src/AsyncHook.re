type state('a, 'e) =
  | Idle
  | Loading
  | Data('a)
  | Error('e);

type action('a, 'e) =
  | SetState(state('a, 'e))
  | Fetch(Promise.t(Belt_Result.t('a, 'e)))
  | SetData('a)
  // Useful for setting your own error when you are using the declarative mode
  | SetError('e);

type api('a, 'e) = {
  state: state('a, 'e),
  setState: state('a, 'e) => unit,
};

/**
  Usage:
  let (createUser, createUserState) = Async.use((~cb, ~name, ~age) => cb(() => {
    fetch("/", ~params={
      name,
      age,
    })
  }))


  let onSubmit= () => {
    createUser(~name=form.values.name, ~age=form.values.age)
  }
 */
let use = fn => {
  let (state, send) =
    ReactUpdate.useReducer(Idle, (action, _state) => {
      switch (action) {
      | SetState(newState) => Update(newState)
      | Fetch(promise) =>
        UpdateWithSideEffects(
          Loading,
          self => {
            let () =
              promise->Promise.get(result => {
                switch (result) {
                | Ok(data) => self.send(SetData(data))
                | Error(msg) => self.send(SetError(msg))
                }
              });

            None;
          },
        )
      | SetData(data) => Update(Data(data))
      | SetError(data) => Update(Error(data))
      }
    });

  let fetchWithArgs =
    fn(~cb=request => {
      let promise = request();
      // dispatch promise instance for declarative usage
      send(Fetch(promise));
      // send same promise instance for local instance handling
      promise;
    });

  ({state, setState: state => send(SetState(state))}, fetchWithArgs);
};

let getData = (state, fn) => {
  switch (state) {
  | Data(data) => fn(data)
  | _ => ()
  };
};

let isData =
  fun
  | Data(_) => true
  | _ => false;
let isLoading =
  fun
  | Loading => true
  | _ => false;
let isError =
  fun
  | Error(_) => true
  | _ => false;
