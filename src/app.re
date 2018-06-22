[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

type state = {weather: option(WeatherData.weather)};

type action =
  | WeatherLoaded(WeatherData.weather);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {weather: None},
  didMount: self => {
    let handleWeatherLoaded = weather => self.send(WeatherLoaded(weather));

    WeatherData.getWeather()
    |> Js.Promise.then_(weather => {
         handleWeatherLoaded(weather);
         Js.Promise.resolve();
       })
    |> ignore;
  },
  reducer: (action, _prevState) =>
    switch (action) {
    | WeatherLoaded(newWeather) =>
      ReasonReact.Update({weather: Some(newWeather)})
    },
  render: self =>
    <div className="App">
      <p>
        (
          switch (self.state.weather) {
          | None => ReasonReact.string("Loading weather...")
          | Some(weather) => ReasonReact.string(weather.summary)
          }
        )
      </p>
      <h1> (ReasonReact.string("IT'S ALIVE!!!!!!!!!")) </h1>
    </div>,
};