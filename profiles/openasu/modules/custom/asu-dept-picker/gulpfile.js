var gulp = require('gulp');
var source = require('vinyl-source-stream');
var browserify = require('browserify');
var watchify = require('watchify');
var reactify = require('reactify');
var notifier = require('node-notifier');
var concat = require('gulp-concat');
var sass = require('gulp-sass');
var watch = require('gulp-watch');
var copy = require('gulp-copy');

var notify = function(error) {
  var message = 'In: ';
  var title = 'Error: ';

  if(error.description) {
    title += error.description;
  } else if (error.message) {
    title += error.message;
  }

  if(error.filename) {
    var file = error.filename.split('/');
    message += file[file.length-1];
  }

  if(error.lineNumber) {
    message += '\nOn Line: ' + error.lineNumber;
  }

  notifier.notify({title: title, message: message});
};

var bundler = watchify(browserify({
  entries: ['./src/main.jsx'],
  transform: [reactify],
  extensions: ['.jsx'],
  debug: true,
  cache: {},
  packageCache: {},
  fullPaths: false
}));

function bundle() {
  return bundler
    .external('react')
    .external('react-dom')
    .bundle()
    .on('error', notify)
    .pipe(source('asu_dept_picker.react.js'))
    .pipe(gulp.dest('./'))
}
bundler.on('update', bundle);

gulp.task('build', function() {
  bundle()
});

gulp.task('sass', function () {
  gulp.src('./*.scss')
    .pipe(sass().on('error', sass.logError))
    .pipe(concat('asu_dept_picker.css'))
    .pipe(gulp.dest('./'));
});

gulp.task('default', ['build', 'sass', 'watch']);

gulp.task('watch', function () {
  gulp.watch('./*.scss', ['sass']);
});
