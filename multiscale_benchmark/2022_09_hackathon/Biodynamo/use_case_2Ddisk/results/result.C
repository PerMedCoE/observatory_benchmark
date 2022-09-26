void result()
{
//=========Macro generated from canvas: c1/c1
//=========  (Mon Sep 26 19:55:03 2022) by ROOT version 6.25/01
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,700,500);
   c1->SetHighLightColor(2);
   c1->Range(11.57812,783.75,29.33854,3396.25);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetGridx();
   c1->SetGridy();
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle(";Time [days];2D Monolayer size (um)");
   
   Double_t Graph_fx1[16] = {
   14,
   14.83333,
   15.66667,
   16.5,
   17.33333,
   18.16667,
   19,
   19.83333,
   20.66667,
   21.5,
   22.33333,
   23.16667,
   24,
   24.83333,
   25.66667,
   26.5};
   Double_t Graph_fy1[16] = {
   1240,
   1320,
   1360,
   1440,
   1560,
   1640,
   1720,
   1840,
   2000,
   2120,
   2280,
   2440,
   2600,
   2720,
   2880,
   3040};
   TGraph *graph = new TGraph(16,Graph_fx1,Graph_fy1);
   graph->SetName("Graph");
   graph->SetTitle("Sim data ");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ffffff");
   graph->SetFillColor(ci);
   graph->SetFillStyle(1000);

   ci = 1179;
   color = new TColor(ci, 0, 0, 1, " ", 0.2);
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);

   ci = 1180;
   color = new TColor(ci, 0, 0, 1, " ", 0.7);
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.5);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Sim data ",100,12.75,27.75);
   Graph_Graph1->SetMinimum(1060);
   Graph_Graph1->SetMaximum(3220);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph1);
   
   multigraph->Add(graph,"LP");
   
   Double_t Graph_fx2[6] = {
   14,
   16.08333,
   17,
   20.04167,
   21.08333,
   26.91667};
   Double_t Graph_fy2[6] = {
   1140,
   1400,
   1590,
   2040,
   2250,
   3040};
   graph = new TGraph(6,Graph_fx2,Graph_fy2);
   graph->SetName("Graph");
   graph->SetTitle("Exp data ");

   ci = TColor::GetColor("#ffffff");
   graph->SetFillColor(ci);
   graph->SetFillStyle(1000);

   ci = 1182;
   color = new TColor(ci, 0, 0, 0, " ", 0.2);
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);

   ci = 1183;
   color = new TColor(ci, 0, 0, 0, " ", 0.7);
   graph->SetMarkerColor(ci);
   graph->SetMarkerStyle(20);
   graph->SetMarkerSize(0.5);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","Exp data ",100,12.70833,28.20833);
   Graph_Graph2->SetMinimum(950);
   Graph_Graph2->SetMaximum(3230);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph2->SetLineColor(ci);
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetTitleOffset(1);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetZaxis()->SetLabelFont(42);
   Graph_Graph2->GetZaxis()->SetTitleOffset(1);
   Graph_Graph2->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph2);
   
   multigraph->Add(graph,"LP");
   multigraph->Draw("A");
   multigraph->GetXaxis()->SetLimits(13.35417, 27.5625);
   multigraph->GetXaxis()->SetTitle("Time [days]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetTitleOffset(1);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("2D Monolayer size (um)");
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetTitleFont(42);
   
   TLegend *leg = new TLegend(0.1,0.7,0.3,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph","Sim data ","lpf");

   ci = TColor::GetColor("#ffffff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1000);

   ci = 1179;
   color = new TColor(ci, 0, 0, 1, " ", 0.2);
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = 1180;
   color = new TColor(ci, 0, 0, 1, " ", 0.7);
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","Exp data ","lpf");

   ci = TColor::GetColor("#ffffff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1000);

   ci = 1182;
   color = new TColor(ci, 0, 0, 0, " ", 0.2);
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = 1183;
   color = new TColor(ci, 0, 0, 0, " ", 0.7);
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.5);
   entry->SetTextFont(42);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
