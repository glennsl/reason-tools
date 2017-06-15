open Rebase;
open Core;

type state = {
  copyConfirmation: option string, 
  inputRef: option ReasonReact.reactRef
};

let showCopyConfirmation text () state self => {
  Util.setTimeout (self.ReasonReact.update (fun () _ _ => ReasonReact.Update {...state, copyConfirmation: None})) 2500;
  ReasonReact.Update {...state, copyConfirmation: Some text}
};
/*
let updateInputRef nullableRef state _ =>
  switch (Js.Null.to_opt nullableRef) {
  | Some ref => ReasonReact.Update {...state, inputRef: Some ref};
  | None => ReasonReact.NoUpdate
  };
*/
let updateInputRef ref state _ =>
  ReasonReact.SilentUpdate {...state, inputRef: Some ref};

let make ::inText ::inLang ::outText ::outLang ::link ::onOpen ::onInputChanged _ => {
  ...(ReasonReact.statefulComponent "PopupWindow"),
  initialState: fun () => {copyConfirmation: None, inputRef: None},
  didMount: fun state _ => {
    switch state.inputRef {
    | None => ()
    | Some ref =>
      Js.log ref;
      CodeMirror.focus ref;
      CodeMirror.execCommand ref "selectAll"
    };
    ReasonReact.NoUpdate
  },
  render: fun state self =>
    <div style=PopupStyles.popup>
      <div style=PopupStyles.popupColumn>
        <h1 style=PopupStyles.popupContext> <ColumnTitle name="In" lang=inLang /> </h1>
        <Editor
          value=inText
          lang=inLang
          inputRef=(self.update updateInputRef)
          onChange=onInputChanged
        />
      </div>
      <div style=PopupStyles.popupColumn>
        <h1 style=PopupStyles.popupContext>
          <ColumnTitle name="Out" lang=outLang />
          <CopyButton
            style=PopupStyles.contextLink
            label="share"
            text=link
            onCopy=(self.update (showCopyConfirmation "Link copied to clipboard"))
          />
          <CopyButton
            style=PopupStyles.contextLink
            text=outText
            onCopy=(self.update (showCopyConfirmation "Text copied to clipboard"))
          />
          <OpenButton style=PopupStyles.contextIcon onClick=(fun _ => onOpen inText) />
        </h1>
        <Editor value=outText lang=outLang readOnly=true />
        <CopyConfirmation
          style=PopupStyles.copyConfirmation
          show=(Option.isSome state.copyConfirmation)
          text=(Option.getOr "" state.copyConfirmation)
        />
      </div>
    </div>
};