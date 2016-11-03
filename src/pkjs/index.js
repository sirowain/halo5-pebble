Pebble.addEventListener('ready', function() {
  // PebbleKit JS is ready!
  console.log('PebbleKit JS ready!');
  
  haloGetStats('http://halobridge.azurewebsites.net/stats/s1r0w41n');
  //haloGetEmblem('https://www.haloapi.com/profile/h5/profiles/s1r0w41n/emblem?size=95');
  downloadImage();
});

var IMG_URL = 'http://halobridge.azurewebsites.net/emblem/s1r0w41n';
// var IMG_URL = 'https://www.haloapi.com/profile/h5/profiles/s1r0w41n/emblem?size=95';
var MAX_CHUNK_SIZE = 220;  // From app_message_inbox_size_maximum()

function sendChunk(array, index, arrayLength) {
  // Determine the next chunk size
  
  console.log('arrayLength: ' + arrayLength);
  
  var chunkSize;
  
  var isLast = 0;
  if(index < (arrayLength - MAX_CHUNK_SIZE)) {
    // Will require multiple chunks for remaining data
    chunkSize = MAX_CHUNK_SIZE;
  } else {
    // Will only need one more chunk
    chunkSize = arrayLength - index;
    isLast = 1;
  }

  // Prepare the dictionary
  var dict = {
    'DataChunk': array.slice(index, index + chunkSize),
    'ChunkSize': chunkSize,
    'Index': index
  };

  console.log('Will send chunk with index ' + index);
  // Send the chunk
  Pebble.sendAppMessage(dict, function() {
    // Success
    index += chunkSize;

    if(isLast === 0) {
      // Send the next chunk
      sendChunk(array, index, arrayLength);
      console.log('Sent chunk with index ' + index);
    } else {
      // Complete!
      Pebble.sendAppMessage({'Complete': 0}, function(e) {
        console.log('Complete: AppKeyComplete!');
      }, function(e) {
        console.log('Complete: Failed: ' + JSON.stringify(e));
      });
      console.log('Sent chunk COMPLETE');
    }
  }, function(e) {
    console.log('Failed to send chunk with index ' + index);
  });
}

function transmitImage(array) {
  var index = 0;
  var arrayLength = array.length;
  
  // Transmit the length for array allocation
  Pebble.sendAppMessage({'DataLength': arrayLength}, function(e) {
    // Success, begin sending chunks
    sendChunk(array, index, arrayLength);
  }, function(e) {
    console.log('Failed to send data length to Pebble!');
  });
}

function processImage(responseData) {
  // Convert to a array
  var byteArray = new Uint8Array(responseData);
  var array = [];
  for(var i = 0; i < byteArray.byteLength; i++) {
    array.push(byteArray[i]);
  }
  
  console.log('Array data: ' + array.length);

  // Send chunks to Pebble
  transmitImage(array);
}

function downloadImage() {
  var request = new XMLHttpRequest();
  request.onload = function() {
    console.log('Response: ' + this.response);
    processImage(this.response);
  };
  request.responseType = "arraybuffer";
  request.open("GET", IMG_URL);
  request.setRequestHeader('Ocp-Apim-Subscription-Key', '7a59bbd7e14d4c46b8d42e4de5b9a032');
  request.send();
}

function haloGetStats(url)
{
  var method = 'GET';

  // Create the request
  var request = new XMLHttpRequest();

  // Specify the callback for when the request is completed
  request.onload = function() {
    try {
      // Transform in to JSON
      var json = JSON.parse(this.responseText);

      // Read data
      var kd_str = json.totals.kd_str;
      var kills_str = json.totals.totalkills;
      var deaths_str = json.totals.totaldeaths;
      
      var dict = {
        'totals_ratio': kd_str,
        'totals_kills': kills_str,
        'totals_deaths': deaths_str
      };
      
      console.log('JSON: ' + JSON.stringify(dict));
      
      Pebble.sendAppMessage(dict, function() {
        console.log('Message sent successfully: ' + JSON.stringify(dict));
      }, function(e) {
        console.log('Message failed: ' + JSON.stringify(e));
      });
      
    } catch(err) {
      console.log('Error parsing JSON response!');
    }
  };

  // Send the request
  request.open(method, url);
  request.send();
}