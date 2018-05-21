// A sample Node.js script to mark a Statuscope task as failed

var request = require("request");

function signalFailure() {
    // Prepare a JSON object matching task
    var failureJson = '{ "token":"f087c3a1", "status":"KO", "reason":"Connection failed" }';

    // Setting URL and headers for request
    var options = {
        url: 'https://www.statuscope.io/tasks/kBFL49LscBbd3dnna',
        headers: {
            'User-Agent': 'request',
            'Content-Type': 'application/json'
        },
        body: failureJson
    };

    // Return a promise
    return new Promise(function(resolve, reject) {
    	// Do async POST
        request.post(options, function(error, response, body) {
            if (error) {
                reject(error);
            } else {
                resolve(JSON.parse(body));
            }
        })
    });
}

function main() {
    var signalFailurePromise = signalFailure();
    signalFailurePromise.then(function(result) {
        // Display result
        console.log(result);
    }, function(error) {
        console.log(error);
    });
}

main();
