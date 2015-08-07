set http_proxy=http://landysh:pSYzMTZB@proxy:80/
set OS_WGET=wget
rem set OS_WGET=powershell netsh winhttp import proxy source=ie; Import-Module bitstransfer; start-bitstransfer -source 
rem %OS_WGET% http://downloads.sourceforge.net/project/gnuwin32/make/3.81/make-3.81.exe || @ echo "ERROR: Open ./get-utils.bat and modify 'http_proxy' with your valid internet settings" && exit /B
%OS_WGET% http://downloads.sourceforge.net/project/gnuwin32/unzip/5.51-1/unzip-5.51-1.exe
%OS_WGET% http://downloads.sourceforge.net/project/gnuwin32/unzip/5.51-1/unzip-5.51-1-bin.zip
%OS_WGET% http://downloads.sourceforge.net/project/gnuwin32/which/2.20/which-2.20-bin.zip
%OS_WGET% http://downloads.sourceforge.net/project/gnuwin32/coreutils/5.3.0/coreutils-5.3.0-bin.zip
end


