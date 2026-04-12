Get-PnpDevice -Class Bluetooth |
Where-Object {$_.InstanceId -match "DEV_"} |
ForEach-Object {
    if ($_.InstanceId -match "DEV_([0-9A-F]{12})") {
        $mac = $matches[1] -replace '(.{2})', '$1:'
        $mac.TrimEnd(':')
    }
}