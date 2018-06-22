#Reason Weather Fetching

1.  create type for weather

2.  Make App.re stateful which requires variants for state and actions.

Create a state type which references our WeatherData type so when we call state it will compile if the weather record is of type WeatherData. Note that the state type is a record which we can tell by the `{}` syntax.
`type state = {weather: WeatherData.weather};`

Create an action type, give it a name and, in this case tell it to expect a record of type WeatherData. So Whenever we call WeatherLoaded we have to be sure to pass it a record of type WeatherData.weather. This is not referrign to our state type. When we go to update state, it will check if what we pass it is of the WeatherData type. Here we are not doing that. Just passing the action a type of WeatherData to do something else with. The thing we will be doing, is updating the state.

```r
type action =
  | WeatherLoaded(WeatherData.weather);
```

3.  Change the component type to `reducerComponent` since we are handling state.

This means we need to override the `initialState`, `reducer`, properties the we spread in with `...component`

4.  `make`

- notes, initial state is a function that returns a record `{}`
- in our reducer, we need to use the record syntax as well.

```r
let make = _children => {
  ...component,
  initialState: () => {weather: dummyweather},
  reducer: (action, _prevState) =>
    switch (action) {
    | WeatherLoaded(newWeather) => ReasonReact.Update({weather: newWeather})
    },
  render: self =>
    <div className="App">
      <p> (ReasonReact.string(self.state.weather.summary)) </p>
      <p> (ReasonReact.string(string_of_float(self.state.weather.temp))) </p>
    </div>,
};
```
