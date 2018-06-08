// Create Definitions to connect to internet
#define IO_USERNAME "IO_USERNAME" // insert your IO_USERNAME
#define IO_KEY "IO_KEY" // insert your IO_key
#define WIFI_SSID "wifissid" // insert your wifi id
#define WIFI_PASS "wifi_pass" //insert your wifi pass

// Create Instances
HTTPClient http; 
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *Anurag216Score = io.feed("Anurag216Score");

