var http = require('http');
var fs = require('fs');

var requestListener = function (req, res) {
    res.writeHead(200);
    var buffer = fs.readFileSync("binary.jb");
    res.end(buffer);
}

var server = http.createServer(requestListener);
server.listen(8080);
