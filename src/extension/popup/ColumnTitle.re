[@@@bs.config {jsx: 2}];

open Rebase;

let component = ReasonReact.statelessComponent "ColumnTitle";

let showVersion lang =>
  switch lang {
  | Some "RE"
  | Some "REI" => Globals.reasonVersion
  | Some "ML"
  | Some "MLI" => Globals.ocamlVersion
  | _ => ""
  };

let formatTitle name lang => name ^ " (" ^ lang ^ ")";

let make ::name ::lang _ => {
  let title = lang |> Option.mapOr (formatTitle name) name;
  {
    ...component,
    render: fun _ _ =>
      <span title=(showVersion lang) style=PopupStyles.contextTitle>
        (ReactRe.stringToElement title)
      </span>
  }
};
