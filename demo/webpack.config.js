const path = require("path");

module.exports = {
  mode: 'development',
  entry: './src/Index.bs.js',
  module: {
    rules: [
      {
        test: /.js$/,
        exclude: /{node_modules}/,
        use: {
          loader: "babel-loader",
          options: {
            presets: ["@babel/preset-env"],
          },
        },
      },
    ],
  },
  output: {
    path: path.resolve(__dirname, "dist"),
    filename: 'index.bundle.js',
  },
  devServer: {
    compress: true,
  },
};
