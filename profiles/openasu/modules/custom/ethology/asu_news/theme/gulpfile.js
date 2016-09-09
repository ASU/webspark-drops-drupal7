var gulp        = require('gulp');
var $           = require('gulp-load-plugins')();
var browserSync = require('browser-sync').create();
var sass        = require('gulp-sass');
var sourcemaps  = require('gulp-sourcemaps');
var filter      = require('gulp-filter');

gulp.task('sass', function() {
  return gulp.src('scss/asumod.scss')
    .pipe(sourcemaps.init())
    .pipe($.sass().on('error', $.sass.logError))
    .pipe($.autoprefixer({browsers: ['last 2 versions', 'ie >= 9'] }))
    .pipe(sourcemaps.write('.')) 
    .pipe(gulp.dest('css'))
    .pipe(filter('**/*.css'))
    .pipe(browserSync.stream());
});

gulp.task('serve', ['sass'], function() {
    browserSync.init({
        proxy: "dev.asu_modules.local"
    });

    gulp.watch("./scss/**/*.scss", ['sass']);
    gulp.watch(['**/*.php', '**/*.js']).on('change', browserSync.reload);
});

gulp.task('default', ['serve']);