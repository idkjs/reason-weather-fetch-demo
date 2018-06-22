#Reason Weather Fetching

1.  create type for weather

2.  Make App.re stateful which requires variants for state and actions.

Create a state type which references our WeatherData type so when we call state it will compile if the weather record is of type WeatherData \*/
`type state = {weather: WeatherData.weather};`

Create an action type, give it a name and, in this case tell it to expect a record of type WeatherData. So Whenever we call WeatherLoaded we have to be sure to pass it a record of type WeatherData.weather. This is not referrign to our state type. When we go to update state, it will check if what we pass it is of the WeatherData type. Here we are not doing that. Just passing the action a type of WeatherData to do something else with. The thing we will be doing, is updating the state.

```r
type action =
  | WeatherLoaded(WeatherData.weather);
```

3.  Change the component type to `reducerComponent` since we are handling state.
