#!/bin/bash

# Ensure we're on main branch
git checkout main

# Pull latest changes from origin/main
git pull origin main

# Navigate to build directory and build
cd Main/BUILDER
make clean
make all

echo "Pull and build completed!"

