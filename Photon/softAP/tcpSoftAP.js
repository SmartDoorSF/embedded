// Default softAP mode is TCP without browser
var sap = new require('softap-setup')();

sap.deviceInfo(callback);
function callback(err, dat) {
  if (err) { throw err; }
  console.log("Device ID: %s, claimed: %s", dat.id, dat.claimed ? "yes" : "no");
};
