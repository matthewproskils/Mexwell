require.config({ paths: { 'vs': 'https://unpkg.com/monaco-editor@latest/min/vs' }});
window.MonacoEnvironment = { getWorkerUrl: () => proxy };

let proxy = URL.createObjectURL(new Blob([`
	self.MonacoEnvironment = {
		baseUrl: 'https://unpkg.com/monaco-editor@latest/min/'
	};
	importScripts('https://unpkg.com/monaco-editor@latest/min/vs/base/worker/workerMain.js');
`], { type: 'text/javascript' }));

let code = `
fun test() string {
  var return = "e";
}

fun main() void {
  print(test());
}
`.trim();
require(["vs/editor/editor.main"], function () {
	window.editor = monaco.editor.create(document.getElementById('t'), {
    value: code,
		language: 'kotlin',
		theme: 'vs-dark'
	});
});