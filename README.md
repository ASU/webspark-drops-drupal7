# Webspark

This Drupal 7 distribution is built on top of Panopoly (https://drupal.org/project/panopoly) and is maintained by the 
University Techonology Office at Arizona State University (https://asu.edu).

## How to submit a fix/patch for Webspark

1. Fork this Git repo (https://github.com/ASU/webspark-drops-drupal7).
2. Make sure you have checked out the master branch locally and that its latest commit matches the latest commit at 
https://github.com/ASU/webspark-drops-drupal7/tree/master so the codebases match.
3. Create a new local branch called **7.x-ext-patches**. (If this branch already exists locally, make sure it also 
matches the latest commit of https://github.com/ASU/webspark-drops-drupal7/tree/master.)
4. When your patch/fix/code is completed and ready to submit for consideration, commit your changes to your local repo 
on that same 7.x-ext-patches.
5. Push your latest commit up to your Github fork and submit a pull request to the 
https://github.com/ASU/webspark-drops-drupal7 repo. When doing this, be sure to select the correct source 
(<yourID>/7.x-ext-patches) and destination ASU/7.x-ext-patches branches.

This process will let us know that you have submitted a fix for us to review.

*NOTES:*

- All pull requests should ideally be flattened down to one (1) Git commit. (Use git rebase or git reset --mixed && git 
add && git commit to accomplish this.) Failure to do this will delay consideration of your proposed updates.
- Any Git commit messages you write will be public and permanent, so make them useful, concise, and clean. Work with 
commit messages like, "more updates", "Webspark fixes", "#&%#!&%* fixes", etc.
- Please do not attempt to submit any pull requests to the following branches because they will be rejected without 
consideration:
  - master
  - 7.x-rc
  - 7.x-dev

If you have any further questions about this process, please email webconsulting(--AT--)asu(--DOT--)edu.
