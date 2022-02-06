let consoleDiv = document.getElementById('console')
let lastMsg = ''

function format(s)
{
  return s.replaceAll('\t', '&nbsp;&nbsp;&nbsp;&nbsp;').replaceAll('\n', '<br>')
}

out = function () {
  consoleDiv.innerHTML =
    consoleDiv.innerHTML + '<br>' + format(Array.from(arguments).join(' '))
  lastMsg = Array.from(arguments).join(' ')
}

let runMex = Module.cwrap('runMex', 'void', ['string'])
let runMexDebug = Module.cwrap('runMexDebug', 'void', ['string'])

function runAsm() {
  consoleDiv.innerHTML = ''
  try {
    runMex(window.editor.getValue())
    consoleDiv.className = 'success'
  } catch (e) {
    consoleDiv.innerHTML = format(lastMsg) + '<br>' + e.message
    consoleDiv.className = 'error'
  }
}

function runAsmDebug() {
  consoleDiv.innerHTML = ''
  try {
    runMexDebug(window.editor.getValue())
    consoleDiv.className = 'success'
  } catch (e) {
    consoleDiv.innerHTML = (lastMsg) + '<br>' + e.message
    consoleDiv.className = 'error'
  }
}
