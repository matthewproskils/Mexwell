require.config({ paths: { 'vs': 'https://unpkg.com/monaco-editor@latest/min/vs' }});
window.MonacoEnvironment = { getWorkerUrl: () => proxy };

let proxy = URL.createObjectURL(new Blob([`
	self.MonacoEnvironment = {
		baseUrl: 'https://unpkg.com/monaco-editor@latest/min/'
	};
	importScripts('https://unpkg.com/monaco-editor@latest/min/vs/base/worker/workerMain.js');
`], { type: 'text/javascript' }));

require(["vs/editor/editor.main"], function () {
	window.editor = monaco.editor.create(document.getElementById('t'), {
    value: 
`fun test(string i) {
  print(i);
}

fun main() {
  test("hio");
}

var yee = "omg";
print(yee);`,
		language: 'kotlin',
		theme: 'vs-dark'
	});
});