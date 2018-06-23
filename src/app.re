[%bs.raw {|require('./app.css')|}];

type optionOrError('a) =
  | Some('a)
  | None
  | Error;

type state = {weather: optionOrError(WeatherData.weather)};

type action =
  | LoadedWeather(WeatherData.weather)
  | WeatherError;

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {weather: None},
  didMount: self => {
    let handleLoadedWeather = weather => self.send(LoadedWeather(weather));
    let handleWeatherError = () => self.send(WeatherError);

    WeatherData.getWeather()
    |> Js.Promise.then_(weather => {
         handleLoadedWeather(weather);
         Js.Promise.resolve();
       })
    |> Js.Promise.catch(_err => {
         handleWeatherError();
         Js.Promise.resolve();
       })
    |> ignore;
  },
  reducer: (action, _prevState) =>
    switch (action) {
    | LoadedWeather(newWeather) =>
      ReasonReact.Update({weather: Some(newWeather)})
    | WeatherError => ReasonReact.Update({weather: Error})
    },
  render: self =>
    <div className="App">
      <p>
        (
          switch (self.state.weather) {
          | None => ReasonReact.string("Loading weather...")
          | Error => ReasonReact.string("Error loading weather.")
          | Some({summary, temp}) =>
            ReasonReact.string(summary ++ " - " ++ string_of_float(temp))
          }
        )
      </p>
    </div>,
};