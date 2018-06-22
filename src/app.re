[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

/* create a state type which references our WeatherData type so when we call state it will compile if the weather record is of type WeatherData */
type state = {weather: WeatherData.weather};

/* create an action type, give it a name and, in this case tell it to expect a record of type WeatherData. So Whenever we call WeatherLoaded we have to be sure to pass it a record of type WeatherData.weather. This is not referrign to our state type. When we go to update state, it will check if what we pass it is of the WeatherData type. Here we are not doing that. Just passing the action a type of WeatherData to do something else with. The thing we will be doing, is updating the state.*/
type action =
  | WeatherLoaded(WeatherData.weather);
let component = ReasonReact.statelessComponent("App");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (ReasonReact.string(message)) </h2>
      </div>
      <p className="App-intro">
        (ReasonReact.string("To get started, edit"))
        <code> (ReasonReact.string(" src/App.re ")) </code>
        (ReasonReact.string("and save to reload."))
      </p>
    </div>,
};