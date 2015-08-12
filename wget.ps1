param ($url=$Args[0])
$filename = [System.IO.Path]::GetFileName($url)
$webclient = new-object System.Net.WebClient
$isDirect=$webClient.Proxy.IsBypassed("http://module.ru")
if ($isDirect){
	Import-Module BitsTransfer
	Start-BitsTransfer -DisplayName $filename -Source $url -Destination $filename 
	}
else {
	netsh winhttp import proxy source=ie
	$creds=Get-Credential
	$webclient.Proxy.Credentials=$creds
	$webclient.DownloadFile($url,$filename)
}
#$proxy = new-object System.Net.WebProxy "proxy:80"
#$proxy.Credentials = $creds
#$proxy.Credentials = New-Object System.Net.NetworkCredential ($env:USERNAME, $env:PASSWORD)
#$proxy = [System.Net.WebRequest]::GetSystemWebProxy()
#$proxy.Credentials = [System.Net.CredentialCache]::DefaultCredentials
#$proxy.useDefaultCredentials = $true

#$webclient.proxy=$proxy


#$webclient.DownloadFile( "http://savepic.ru/7691336.png","7691336.png")

