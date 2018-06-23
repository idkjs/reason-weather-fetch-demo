type weather = {
  summary: string,
  temp: float,
};
/* bad city data passed in. */
/* let url = "https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22newyork%2C%20france%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys"; */

let url = "https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22paris%2C%20france%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";

let parseWeatherJson = json : weather =>
  Json.Decode.{
    summary: field("text", string, json),
    temp: float_of_string(field("temp", string, json)),
  };

let parseWeatherResultsJson = json =>
  Json.parseOrRaise(json)
  |> Json.Decode.(
       at(
         ["query", "results", "channel", "item", "condition"],
         parseWeatherJson,
       )
     );

let getWeather = () =>
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.text)
    |> then_(jsonText => {
         let result = parseWeatherResultsJson(jsonText);
         resolve(result);
       })
  );