module.exports = function(grunt) {
  grunt.initConfig({
    min: {
      dist: {
        src: ['jquery.breakup.js'],
        dest: 'jquery.breakup.min.js'
      }
    }
  });
};