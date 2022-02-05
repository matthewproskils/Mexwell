async function fetchAndInstantiate()
{
  const response = await fetch("./main.wasm");
  const buffer = await response.arrayBuffer();
  const obj = await WebAssembly.instantiate(buffer, {env: {memory: new WebAssembly.Memory({initial: 256, maximum: 256})}});
  console.log(obj.instance.exports);
}
fetchAndInstantiate();