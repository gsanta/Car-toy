// server.js
const http = require('http');

const server = http.createServer((req, res) => {
  console.log(`${new Date().toISOString()} - ${req.url}`);
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end('Data received\n');
});

server.listen(3000, '0.0.0.0', () => {
  console.log('Server running on port 3000');
});