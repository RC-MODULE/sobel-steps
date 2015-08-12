param ($url=$Args[0])
$webclient = new-object System.Net.WebClient
$proxy = new-object System.Net.WebProxy "proxy:80"
$proxy.Credentials = New-Object System.Net.NetworkCredential ($env:USERNAME, $env:PASSWORD)
#$proxy = [System.Net.WebRequest]::GetSystemWebProxy()
#$proxy.Credentials = [System.Net.CredentialCache]::DefaultCredentials
#$proxy.useDefaultCredentials = $true

$webclient.proxy=$proxy
$filename = [System.IO.Path]::GetFileName($url)
$webclient.DownloadFile($url,$filename)
$webclient.DownloadFile($url,$filename)
