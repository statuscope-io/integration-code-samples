# A sample PowerShell script to check the status of a Windows service

$ServiceName = 'OpenVPNService'
$arrService = Get-Service -Name $ServiceName

# Token is obligatory for every request
$params = @{
 "token"="a522a38f";
}

# Add 'status' and 'reason' w.r.t. status of the service
if ($arrService.Status -ne 'Running')
{
    $params += @{"status"="KO";}
    $params += @{"reason"="Unknown";}
}
else
{
    $params += @{"status"="OK";}
}

# Note how request body is converted to JSON on the go
Invoke-WebRequest -Uri https://staging.statuscope.io/tasks/ZrnnL9nis4n934qqm -Method POST -Body ($params|ConvertTo-Json) -ContentType "application/json"
