#!/bin/bash

# Save current branch name
CURRENT_BRANCH=$(git branch --show-current)

# Stage all files
git add .

# Commit changes
git commit -m "most recent commit" || echo "No changes to commit"

# Switch to main branch
git checkout main

# Merge current branch into main (if not already on main)
if [ "$CURRENT_BRANCH" != "main" ]; then
    git merge "$CURRENT_BRANCH" --no-edit || echo "Merge conflicts or already merged"
fi

# Push main to GitHub
git push origin main

# Switch back to original branch
if [ "$CURRENT_BRANCH" != "main" ]; then
    git checkout "$CURRENT_BRANCH"
fi

echo "Deployed to main branch. Current branch: $CURRENT_BRANCH"
