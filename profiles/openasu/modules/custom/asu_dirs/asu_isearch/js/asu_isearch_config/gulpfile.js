var gulp = require('gulp');
var react = require('gulp-react');
var concat = require('gulp-concat');

gulp.task('default', function () {
    return gulp.src('src/*.jsx')
        .pipe(react())
        .pipe(concat('asu_isearch_config.js'))
        .pipe(gulp.dest('./'));
});
