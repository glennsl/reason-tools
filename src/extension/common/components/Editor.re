let make ::value ::lang ::defaultValue=? ::readOnly=false ::ref=? ::onChange=? _ => {
  ...(ReasonReact.statelessComponent "Editor"),
  render: fun _ _ =>
    <CodeMirror
      value=value
      ref=?ref
      defaultValue=?defaultValue
      onChange=?onChange
      options={
        "mode": lang == Some "ML" ? "text/x-ocaml" : "javascript",
        "theme": "oceanic-next",
        "readOnly": Js.Boolean.to_js_boolean readOnly
      }
    />
};