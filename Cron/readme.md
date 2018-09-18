# How to integrate Statuscope into a cronjob?

Your systems will talk to Statuscope through HTTP rest commands, so in the easiest way possible you will want to use `cURL` to talk to Statuscope. Let's say you have a script named `ftp_image_backup.sh` that takes disk images of your FTP server, and that you want to connect this task to Statuscope. At this point, we will just assume that your script returns `0` upon success as stated in http://tldp.org/LDP/abs/html/exit-status.html,

> Well-behaved UNIX commands, programs, and utilities return a 0 exit code upon successful completion, though there are some exceptions.

You probably have already a cronjob that runs your script `ftp_image_backup.sh`.

    0 * * * * /root/workspace/scripts/ftp_image_backup.sh

In order to let Statuscope know about the result of it, you need to chain up a `cURL` command as shown below.

    0 * * * * /root/workspace/scripts/ftp_image_backup.sh && curl -H "Content-Type: application/json" -X POST -d '{"token":"45a586e6", "status":"OK"}' https://www.statuscope.io/tasks/fcPHcXhJahX14vvxa

Note that, `&&` operator lets the second command to run only if the first one was terminated successfully, hence returning 0.

Have questions? Send them to [hello@statuscope.io](hello@statuscope.io).
