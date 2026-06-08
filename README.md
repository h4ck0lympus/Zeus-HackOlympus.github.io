# blog

- `hugo server -D` runs the local dev server with drafts enabled.
- `hugo` builds the site into `public/`.
- `hugo --minify` builds a production-style output with minification enabled.

## Wide Graphviz Diagrams

If a computation graph is too wide for the post column, generate it as SVG and render it with the `diagram` shortcode in wide mode so it stays readable and scrolls horizontally when needed.

Generate the SVG:

```sh
dot -Tsvg static/images/graph.dot -o static/images/graph.svg
```

Embed it in a post:

```md
{{< diagram path="/images/graph.svg" alt="Computation graph" wide="true" >}}
```
