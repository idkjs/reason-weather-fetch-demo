/* create an action type with three options */
type result =
  | Win
  | Lose
  | Draw;

/* create a function that takes an results and switches based on the action.
   The compiler is inferring that `r` is of the type defined in this file. Given that it's inferring the `result` type, it realizes that one of the options is misssing and tells us by the squiggly green lines. If you hover over them you get a nice message. */
let getPoints = r =>
  switch (r) {
  | Win => 3
  | Lose => 0
  };