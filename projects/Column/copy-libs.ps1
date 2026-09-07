$ErrorActionPreference = 'Stop'

$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $projectRoot

function Sync-Dir {
    param(
        [Parameter(Mandatory = $true)][string]$Source,
        [Parameter(Mandatory = $true)][string]$Destination
    )

    if (-not (Test-Path $Source)) {
        throw "Missing source directory: $Source"
    }

    if (Test-Path $Destination) {
        Remove-Item -Recurse -Force $Destination
    }

    New-Item -ItemType Directory -Force -Path $Destination | Out-Null
    Copy-Item -Recurse -Force (Join-Path $Source '*') $Destination
}

function Sync-File {
    param(
        [Parameter(Mandatory = $true)][string]$Source,
        [Parameter(Mandatory = $true)][string]$Destination
    )

    if (-not (Test-Path $Source)) {
        throw "Missing source file: $Source"
    }

    $destinationParent = Split-Path -Parent $Destination
    New-Item -ItemType Directory -Force -Path $destinationParent | Out-Null
    Copy-Item -Force $Source $Destination
}

Sync-Dir -Source '../../libs/motors/stepper_motor' -Destination 'lib/motors/stepper_motor'
Sync-Dir -Source '../../libs/system/timer' -Destination 'lib/system/timer'
Sync-File -Source '../../libs/input/command_handler.h' -Destination 'lib/input/command_handler.h'
Sync-Dir -Source '../../libs/input/joystick' -Destination 'lib/input/joystick'
Sync-Dir -Source '../../libs/motion/belt' -Destination 'lib/motion/belt'
Sync-Dir -Source '../../libs/logic/limit_switch' -Destination 'lib/logic/limit_switch'
Sync-Dir -Source '../../libs/communication/radio_transmitter' -Destination 'lib/communication/radio_transmitter'

Write-Output 'copy-libs complete'
