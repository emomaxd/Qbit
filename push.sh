#!/bin/bash

# Get the first line of the file
token=$(head -n 1 token.txt)
url=$(head -n 1 github_url.txt)

# Set the remote URL to use the token for authentication
git remote set-url origin https://$token@$url   # Syntax of permanent auth


# Push to the remote repository
git push origin master


                            #     NO NEED TO USE THIS SCRIPT   #