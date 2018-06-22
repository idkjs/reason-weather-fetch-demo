[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

/* create a state type which references our WeatherData type so when we call state it will compile if the weather record is of type WeatherData */
type state = {weather: WeatherData.weather};

/* create an action type, give it a name and, in this case tell it to expect a record of type WeatherData. So Whenever we call WeatherLoaded we have to be sure to pass it a record of type WeatherData.weather. This is not referrign to our state type. When we go to update state, it will check if what we pass it is of the WeatherData type. Here we are not doing that. Just passing the action a type of WeatherData to do something else with. The thing we will be doing, is updating the state.*/
type action =
  | WeatherLoaded(WeatherData.weather);
let component = ReasonReact.reducerComponent("App");

/* create dummy data, give it a name and the type of our records, WeatherData.weather
   Remember that summary was a string type and temp was a float type.*/

let dummyweather: WeatherData.weather = {
  summary: "Warm throughout the day",
  temp: 30.5,
};

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