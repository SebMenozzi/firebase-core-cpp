#!/bin/sh

# Install protos
protogen_repo_url="git@github.com:SebMenozzi/protogen.git"

if [ "$#" -eq 1 ]; then
    git clone -b $1 $protogen_repo_url
else
    git clone $protogen_repo_url
fi

rm -rf src/proto
mkdir src/proto

find './protogen/generated' -name '*.h' -exec mv '{}' './src/proto/' ';'
find './protogen/generated' -name '*.cc' -exec mv '{}' './src/proto/' ';'

rm -rf protogen
