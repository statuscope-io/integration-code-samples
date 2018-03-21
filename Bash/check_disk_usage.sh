#!/bin/bash

# A sample script that notifies Statuscope.io of available disk space in /home

disk_usage=$(df --output=pcent /home | tr -dc '0-9')

if [[ disk_usage -gt 90 ]]; then
    echo "Disk usage is more than 90%"
    curl -H "Content-Type: application/json" \
         -X POST \
         -d '{"token":"6e47283c2c6034d43fd70f123d63d7f2", "status":"KO", "reason": "/home is almost full"}' \
         https://www.statuscope.io/tasks/TZ4CdJaMidAc2DshE
else
    echo "Disk usage is less than 90%"
    curl -H "Content-Type: application/json" \
         -X POST \
         -d '{"token":"6e47283c2c6034d43fd70f123d63d7f2", "status":"OK"}' \
         https://www.statuscope.io/tasks/TZ4CdJaMidAc2DshE
fi

