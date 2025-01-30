# Contributing Guidelines
We are excited to have you contribute to our project! Please follow the steps below to help make the process as smooth as possible.

## How to Contribute
You can find areas where you can contribute by checking out the [Issues](https://github.com/emomaxd/qbit/issues) and [Projects](https://github.com/emomaxd/qbit/projects) pages.

### Reporting Bugs
If you find a bug, please open an [issue](https://github.com/emomaxd/qbit/issues) on GitHub. Be sure to include:
- A description of the bug
- Steps to reproduce the bug
- Any relevant error messages or logs

### Feature Requests
If you'd like to suggest a new feature, open an issue and describe the feature in detail. Please explain why you think it would be useful to the project.

### Contribution Workflow:
- Fork the repository.
- Create a new branch for your changes.
- Implement your changes.
- Open a pull request with a clear description of your changes.

## Code Style
Please follow the code style of the existing project. Consistency is key, and it helps everyone understand and maintain the code. It is expected that names (variables, functions and classes) to be clear and descriptive, reducing the need for comments (most of the time).

- Add comments where necessary to explain complex code.
- Make sure to test your changes before submitting.
- Use the .clang-format file in the root to fix the format of your new implementation.

## Control your commits
Try to make simple PRs that handle one specific topic. Just like for reporting issues, it's better to open 3 different PRs that each address a different issue than one big PR with three commits. This makes it easier to review, approve, and merge the changes independently.

When updating your fork with upstream changes, please use git pull --rebase to avoid creating "merge commits". Those commits unnecessarily pollute the git history when coming from PRs.

Also try to make commits that bring the engine from one stable state to another stable state, i.e. if your first commit has a bug that you fixed in the second commit, try to merge them together before making your pull request. This includes fixing build issues or typos, adding documentation, etc.

## Commit Style
How you format your commit messages is crucial to keeping the commit history and changelog clear and easy to follow. A Git commit message consists of a short title (the first line) and an extended description (everything after the first line with an empty line in between).

It should be written in English, start with a capital letter, and usually use the verb in imperative form (e.g., "Fix" instead of "Fixed"). For example:

- **Fix** bug in rendering pipeline.
- **Add** MetalAPI support for iOS.
- **Improve** performance of asset manager.
- **Core:** Fix issue with Object::has_method().

If your commit resolves a **reported issue**, mention it in the PR description (not the title or commit message) using GitHub's closing keywords like "Fixes #1234". This will automatically close the issue when the PR is merged. While it might be easier to add it to the commit message, it can flood the issue tracker and distract from the main thread.

## License
By contributing to this project, you agree that your contributions will be licensed under the project's existing license.

Thank you for contributing! 
